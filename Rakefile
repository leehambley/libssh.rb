require 'rake/testtask'
require 'rake/extensiontask'

Rake::ExtensionTask.new('libssh.rb')

Rake::TestTask.new(:test => :compile) do |t|
  t.test_files = FileList['test/**/test*.rb']
  t.verbose = true
end

task :default => :test
