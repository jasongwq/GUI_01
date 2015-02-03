#include "UI.h"

void Window::EventDetection(void)
{
    tp_dev.scan(0);
            for (int i = 0; i < Obj_count[0]; ++i)
            {
                pButton[i]->EventDetection();
            }
						for (int i = 0; i < Obj_count[1]; ++i)
            {
                pSwitchButton[i]->EventDetection();
            }
}
void Window::Refresh(void)
{
    Window::draw();
    for (int i = 0; i < Obj_count[0]; ++i)
    {
        pButton[i]->Refresh();
    }
		for (int i = 0; i < Obj_count[1]; ++i)
    {
        pSwitchButton[i]->Refresh();
    }
    ui.current_window = name;
}
