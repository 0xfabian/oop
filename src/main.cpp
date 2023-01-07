#include <rlutil.h>
#include "app.h"
#include "console.h"

int main()
{
    App app;
    Console& con = Console::get_instance();

    con.link(&app);
    con.run();
}