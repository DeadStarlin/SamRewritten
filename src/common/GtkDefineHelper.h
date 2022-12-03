#pragma once

// Ubuntu 18.04 only ships gtkmm 3.22, which doesn't define Gtk::make_managed.
// But it's easy enough to define it if it's not defined
