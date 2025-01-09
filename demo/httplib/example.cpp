#include <iostream>
#include "httplib.h"

int main(){

    // HTTP
    httplib::Server svr;

    svr.Post("/post_test", [](const httplib::Request& req, httplib::Response& res){
        std::cout << "response" << std::endl;
        res.set_content("response", "text/plain");
    });

    svr.Get("/get_test", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    svr.listen("0.0.0.0", 5000);

    return 0;
}
