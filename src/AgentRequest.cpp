//
// Created by tommy on 12.06.17.
//

#include "AgentRequest.h"

AgentRequest::SharedPtr AgentRequest::Create() {
    return AgentRequest::SharedPtr(new AgentRequest());
}
