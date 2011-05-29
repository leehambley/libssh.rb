#include <libsshrb.h>

VALUE rb_mLibSSH;
VALUE rb_cLibSSH_Connection;

VALUE rb_eLibSSH_Error;
VALUE rb_eLibSSH_ConnectionError;

int set_ssh_options_iterator(VALUE, VALUE, VALUE);

void Init_libsshrb()
{
  rb_mLibSSH = rb_define_module("LibSSH");
  Init_libsshrb_constants();
  Init_rb_clibssh_connection();
}

void Init_libsshrb_constants()
{
  rb_eLibSSH_Error = rb_define_class_under(rb_mLibSSH, "Error", rb_eStandardError);
  rb_eLibSSH_ConnectionError = rb_define_class_under(rb_mLibSSH, "ConnectionError", rb_eLibSSH_Error);
}

void Init_rb_clibssh_connection()
{
  rb_cLibSSH_Connection = rb_define_class_under(rb_mLibSSH, "Connection", rb_cObject);
  rb_define_alloc_func(rb_cLibSSH_Connection, alloc_rb_libssh_connection);
  rb_define_method(rb_cLibSSH_Connection, "initialize", initialize_rb_clibssh_connection, 2);
  rb_define_method(rb_cLibSSH_Connection, "connected?", rb_clibssh_connection_connected_q, 0);
  rb_define_method(rb_cLibSSH_Connection, "hostname",   rb_clibssh_connection_hostname, 0);
  rb_define_method(rb_cLibSSH_Connection, "connect",    rb_clibssh_connection_connect, 0);
}

VALUE rb_clibssh_connection_connected_q(VALUE self)
{
  RB_SSH_CONNECTION *rb_ssh_connection;
  Data_Get_Struct(self, RB_SSH_CONNECTION, rb_ssh_connection);
  if(rb_ssh_connection->connected == 1){
    return Qtrue;
  }else{
    return Qfalse;
  }
}

VALUE rb_clibssh_connection_hostname(VALUE self)
{
  LOCAL_SSH_CONNECTION_STRUCT_MACRO;
  VALUE rb_shostname = ENCODED_STR_NEW2(rb_ssh_connection->hostname, "UTF-8");
  return rb_shostname;
}

VALUE initialize_rb_clibssh_connection(VALUE self, VALUE hostname, VALUE options)
{
  LOCAL_SSH_CONNECTION_STRUCT_MACRO;

  rb_ssh_connection->hostname = StringValuePtr(hostname);

  ssh_options_set(rb_ssh_connection->libssh_session, SSH_OPTIONS_HOST, rb_ssh_connection->hostname);
  ssh_options_set(rb_ssh_connection->libssh_session, SSH_OPTIONS_USER, "root");

  rb_hash_foreach(options, set_ssh_options_iterator, self);

  return rb_cLibSSH_Connection;
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

VALUE rb_clibssh_connection_connect(VALUE self)
{
  int rc;
  LOCAL_SSH_CONNECTION_STRUCT_MACRO;

  if( ssh_connect(rb_ssh_connection->libssh_session) == SSH_ERROR )
  {
    rb_raise(rb_eLibSSH_ConnectionError, "Error establishing Connection");
  }

  fprintf(stderr, "Success would be: %i\n", SSH_AUTH_SUCCESS);
  rc = ssh_userauth_autopubkey(rb_ssh_connection->libssh_session, NULL);
  if( rc == SSH_AUTH_SUCCESS )
  {

  } else {
    rb_raise(rb_eLibSSH_ConnectionError, "Error authenticating");
  }

  fprintf(stderr, "Actual return code is: %i\n", rc);
  fprintf(stderr, "Authentication failed: %s\n", ssh_get_error(rb_ssh_connection->libssh_session));
  return Qtrue;
}

int set_ssh_options_iterator(VALUE opt_key, VALUE opt_value, VALUE self)
{
  int success;
  char *key = rb_id2name(SYM2ID(opt_key));
  RB_SSH_CONNECTION *rb_ssh_connection;
  ssh_session session;

  Data_Get_Struct(self, RB_SSH_CONNECTION, rb_ssh_connection);
  session = rb_ssh_connection->libssh_session;

  if ( strcmp(key, "port") == 0)
  {
    printf("will set port to: %d\n", NUM2INT(opt_value));
    int port = NUM2INT(opt_value);
    success = ssh_options_set(session, SSH_OPTIONS_PORT, &port);
  } else {
    rb_raise(rb_eStandardError, "unrecognized option: %s\n", key);
  }
  return success;
}

