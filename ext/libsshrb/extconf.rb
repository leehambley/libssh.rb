require 'mkmf'

extension_name = 'libsshrb'

dir_config(extension_name, '/opt/local/include', '/opt/local/lib')

unless find_header('libssh/libssh.h')
  abort("libssh.h was not found, please install the package")
end

unless find_library('ssh', 'ssh_new')
  abort("`ssh_new()` was not found in libssh, please check that the package is correctly installed")
end

create_makefile extension_name
