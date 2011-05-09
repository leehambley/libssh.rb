require 'rake/testtask'
require 'rake/extensiontask'

Rake::ExtensionTask.new('libsshrb')

Rake::TestTask.new(:test => :compile) do |t|
  t.test_files = FileList['test/**/test*.rb']
  t.verbose = true
end

task :default => :test
