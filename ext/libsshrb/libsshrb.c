#include <libsshrb.h>

VALUE rb_mlibssh;

void Init_libsshrb()
{
  rb_mlibssh = rb_define_module("LibSSH");
}
