#include <iostream>
#include "strlib.h"
#include "RouterNode.h"


using namespace std;

int main() {

    string uri = "/users/find/id";
    string search = "/users/";
    cout << "Hello, World!" << std::endl;

    bool matched = startsWith(uri, search);

    cout << "Found: " << matched << endl;

    RouterNode *rn = new RouterNode("/api", 3);
    rn->addChild("/v1", 5);
    rn->addChild("/v2", 6)->addChild("/users", 7);

    RouteResult *res = rn->findRoute("/api/v2/users");
    if(res->controller_id){
        cout << "Controller Found: " << res->controller_id << endl;
    } else {
        cout << "Controller NOT FOUND" << endl;
    }

    return 0;

}