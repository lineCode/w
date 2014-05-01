#include <w>
#include "models.hpp"

namespace app {
  w::Response index(w::Request& req) {
    p::Context ctx;
    auto posts = p::from<Post>(ctx).where(p::column(&Post::published_at) <= DateTime::now()).order(&Post::published_at).reverse_order();
    auto all = posts.all();
    return w::not_found();
  }

  w::Response get_post(w::Request& req) {
    w::fail<w::Error>("Hello, errors!");
    return w::not_found();
  }
}

int main(int argc, char const *argv[])
{
  p::setup("postgresql://wayward_examples@localhost/wayward_examples_blog");

  w::App app;
  app.get("/", app::index);
  app.get("/posts/:id", app::get_post);

  return app.listen_and_serve("0.0.0.0", 3000);
}
