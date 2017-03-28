//
// Created by Snytkine, Dmitri (CORP) on 3/27/17.
//

#ifndef ROUTER_COUNTER_H
#define ROUTER_COUNTER_H





namespace router_lib {

    template<typename T>
    numNodes(int counter, RouterNode<T> *node) {


        if(node->children.size() == 0){
            return counter;
        } else {
            for(auto &&child: node->children){
                return RouterNode::numNodes(counter + child->children.size(), child);
            }
        }

    }
}
#endif //ROUTER_COUNTER_H
