#include "canvas_body.h"
#include <canvas_view.h>


bool canvas_body::init()
{
    this->setScene(scene_.get());
    return true;
}
