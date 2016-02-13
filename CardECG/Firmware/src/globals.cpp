#include "globals.hpp"

Globals Globals::instance_internal;

Globals::Globals(){
	uart.init(115200);
}

Globals &Globals::instance(){
	return instance_internal;
}

