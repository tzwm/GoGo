#include<gtkmm.h>

int main(int argc, char* argv[]){
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "me.tzwm.GoGo");

    Gtk::ApplicationWindow window; 

    return app->run(window);
}

