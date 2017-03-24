//
// Created by Snytkine, Dmitri (CORP) on 3/22/17.
//
#ifndef ROUTER_FACTORY_H
#define ROUTER_FACTORY_H

#include "RouterNode.h"
#include "PathParamNode.h"
#include "FuncParamNode.h"
#include "constants.h"

namespace router_lib {

    RouterNode *createRouterNode(const std::string nodeUri, void* pVoid, const std::string name);

    RouterNode *createRouterNode(const std::string nodeUri);

//    RouteResult* getNodeResult_(RouterNode *node, const std::string uri, paramsList *params = new paramsList()) const;

  //  RouteResult* getPathNodeResult_(RouterNode *node, const std::string uri, paramsList *params = new paramsList()) const;

    // RouteResult* getFuncNodeResult_(RouterNode *node, const std::string uri, paramsList *params = new paramsList()) const;
}

#endif //ROUTER_NODE_RESULT_H

