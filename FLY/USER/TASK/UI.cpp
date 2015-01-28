#include "UI.h"

MINI_GUI ui;
void Window::event_detection(void)
{
    tp_dev.scan(0);
    if (tp_dev.sta & TP_PRES_DOWN)
    {
        if (tp_dev.x < lcddev.width && tp_dev.y < lcddev.height&&ui.current_window==name)
        {
            for (int i = 0; i < Button_count; ++i)
            {
                pButton[i]->event_detection();
            }
        }
    }
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
