#ifndef CPP_TEST_HELLO_HANDLER_H
#define CPP_TEST_HELLO_HANDLER_H

#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/json/serialize.hpp>

struct BaseResponse {
    bool success;
    std::string message;
};

userver::formats::json::Value Serialize(
    const BaseResponse &response,
    userver::formats::serialize::To<userver::formats::json::Value>) {
    userver::formats::json::ValueBuilder builder;
    builder["success"] = response.success;
    builder["message"] = response.message;
    return builder.ExtractValue();
}

class HelloHandler final : public userver::server::handlers::HttpHandlerJsonBase {
public:
    static constexpr std::string_view kName = "handler-hello";
    using HttpHandlerJsonBase::HttpHandlerJsonBase;

    userver::formats::json::Value HandleRequestJsonThrow(
        const userver::server::http::HttpRequest &request,
        const userver::formats::json::Value &request_json,
        userver::server::request::RequestContext &) const override {
        const auto &name = request.GetArg("name");

        BaseResponse response;
        if (name.empty()) {
            response.success = false;
            response.message = "Name parameter is required";
        } else {
            LOG_INFO() << name;
            response.success = true;
            response.message = fmt::format("Hello, {}!", name);
        }

        // Теперь можно превратить структуру в json::Value одной строкой
        return userver::formats::json::ValueBuilder(response).ExtractValue();
    }
};

#endif // CPP_TEST_HELLO_HANDLER_H
