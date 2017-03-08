#include "canvas_body.h"



bool canvas_body::init()
{
    this->setScene(scene_.get());
    return true;
}
