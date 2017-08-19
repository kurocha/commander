# Teapot v2.0.0 configuration generated at 2017-08-19 22:21:11 +1200

required_version "2.0"

# Project Metadata

define_project "commander" do |project|
	project.title = "Commander"
	project.summary = 'A command line parser and model.'
	
	project.license = 'MIT License'
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = '0.1.0'
end

# Build Targets

define_target 'commander-library' do |target|
	target.build do
		source_root = target.package.path + 'source'
		copy headers: source_root.glob('Commander/**/*.{h,hpp}')
		build static_library: 'Commander', source_files: source_root.glob('Commander/**/*.cpp')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends 'Language/C++14', private: true
	
	target.provides 'Library/Commander' do
		append linkflags [
			->{install_prefix + 'lib/libCommander.a'},
		]
	end
end

define_target 'commander-test' do |target|
	target.build do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: 'Commander', source_files: test_root.glob('Commander/**/*.cpp'), arguments: arguments
	end
	
	target.depends 'Language/C++14', private: true
	
	target.depends 'Library/UnitTest'
	target.depends 'Library/Commander'
	
	target.provides 'Test/Commander'
end

# Configurations

define_configuration 'development' do |configuration|
	configuration[:source] = "https://github.com/kurocha"
	configuration.import "commander"
	
	# Provides all the build related infrastructure:
	configuration.require 'platforms'
	
	# Provides unit testing infrastructure and generators:
	configuration.require 'unit-test'
	
	# Provides some useful C++ generators:
	configuration.require 'generate-cpp-class'
	
	configuration.require "generate-project"
	configuration.require "generate-travis"
end

define_configuration "commander" do |configuration|
	configuration.public!
end
