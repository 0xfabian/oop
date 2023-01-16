#include <rlutil.h>
#include <cstdlib>
#include <ctime>

#include "app.h"
#include "console.h"

int main()
{
    srand((unsigned)time(nullptr));

    App app;
    Console& con = Console::get_instance();

    con.link(&app);
    con.run();
}