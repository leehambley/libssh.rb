require 'mkmf'

unless find_header('libssh.h')
  abort("libssh.h was not found, please install the package")
end
  
unless find_library('ssh2', 'libssh_session_init_ex')
  abort("libssh was not found, please install the package")
end

create_makefile 'libssh.rb'