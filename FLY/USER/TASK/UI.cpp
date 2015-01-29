#include "UI.h"

MINI_GUI ui;
void Window::event_detection(void)
{
    tp_dev.scan(0);
    
            for (int i = 0; i < Button_count; ++i)
            {
                pButton[i]->event_detection();
            }
//        }
//    }
}
void Window::Refresh(void)
{
    Window::draw();
    for (int i = 0; i < Button_count; ++i)
    {
        pButton[i]->Refresh();
    }
    ui.current_window = name;
}
