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


    RouterNode *createRouterNode(const string nodeUri, void* pVoid, const string name);


    RouterNode *createRouterNode(string nodeUri);
}

#endif //ROUTER_NODE_RESULT_H

