#include <libsshrb.h>

VALUE rb_mlibssh;
VALUE rb_clibssh_connection;

VALUE rb_elibssh_error;
VALUE rb_elibssh_connection_error;

void Init_libsshrb()
{
  rb_mlibssh = rb_define_module("LibSSH");
  Init_rb_libssh_constants();
  Init_rb_clibssh_connection();
}

void Init_rb_libssh_constants()
{
  rb_elibssh_error = rb_define_class_under(rb_mlibssh, "Error", rb_eStandardError);
  rb_elibssh_connection_error = rb_define_class_under(rb_mlibssh, "ConnectionError", rb_elibssh_error);
}

void Init_rb_clibssh_connection()
{
  rb_clibssh_connection = rb_define_class_under(rb_mlibssh, "Connection", rb_cObject);
  rb_define_alloc_func(rb_clibssh_connection, alloc_rb_libssh_connection);
  rb_define_method(rb_clibssh_connection, "initialize", initialize_rb_clibssh_connection, -1);
}

VALUE initialize_rb_clibssh_connection(int argc, VALUE *argv, VALUE rb_clibssh_connection)
{
  // Require at least a hostname
  if(argc < 1)
    rb_raise(rb_eArgError, "");
  //
  // –> How should I access RB_SSH_CONNECTION here to store the hostname there, too?
  //
  RB_SSH_CONNECTION *rb_ssh_connection;
  /* Data_Get_Struct(rb_ssh_connection, RB_SSH_CONNECTION, rb_ssh_connection);*/
  
  return rb_clibssh_connection;
}

VALUE alloc_rb_libssh_connection(VALUE class)
{
  RB_SSH_CONNECTION *rb_ssh_connection = malloc(sizeof(RB_SSH_CONNECTION));
  rb_ssh_connection->libssh_session = ssh_new();
  if(rb_ssh_connection->libssh_session == NULL)
    rb_fatal("Unable to alloc at c function ssh_new()");
  VALUE obj = Data_Wrap_Struct(class, 0, free_rb_libssh_connection, rb_ssh_connection);
  return obj;
}

void free_rb_libssh_connection(RB_SSH_CONNECTION *rb_ssh_connection)
{
  ssh_free(rb_ssh_connection->libssh_session);
  free(rb_ssh_connection);
}

