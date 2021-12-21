#include "Router.h"

#include "ErrorResponse.h"

void Router::addMethod(std::string method, Steps steps) {
    m_methodSteps.emplace(method, steps);
}

std::string Router::processRoute(const std::string &requestData, ClientData& clientData, MainMenu& mainMenu) {
    std::string method = getRequestMethod(requestData);

    auto stepsIterator = m_methodSteps.find(method);
    if (stepsIterator != m_methodSteps.end()) {
        Steps steps = stepsIterator->second;
        steps.request->parse(getRequestJsonData(requestData));
        steps.handler->process(steps.request, steps.response, clientData, mainMenu);
        return method + " " + steps.response->toJSON();
    }

    ErrorResponse response;
    return response.toJSON();
}

std::string Router::getRequestMethod(const std::string &requestData) {
    std::size_t pos = requestData.find(' ');
    if (pos == std::string::npos) {
        return "";
    }
    return requestData.substr(0, pos);
}

std::string Router::getRequestJsonData(const std::string &requestData) {
    std::size_t pos = requestData.find(' ');\
    if (pos == std::string::npos) {
        return "";
    }
    return requestData.substr(pos + 1, requestData.size() - pos - 1);
}

Router::~Router() {
    for (const auto &pair: m_methodSteps) {
        Steps steps = pair.second;
        delete steps.handler;
        delete steps.request;
        delete steps.response;
    }
}