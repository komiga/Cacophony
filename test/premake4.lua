
dofile("../premake_common.lua")

function make_test(group, name, srcglob, configs)
	precore.make_project(
		group .. "_" .. name,
		"C++", "ConsoleApp",
		"./", "out/",
		nil, configs
	)

	if nil == configs then
		precore.apply("cacophony-strict")
	end

	if nil == srcglob then
		srcglob = name .. ".cpp"
	end

	configuration {}
		targetname(name)
		files {
			srcglob
		}
end

function make_tests(group, tests)
	for name, test in pairs(tests) do
		make_test(group, name, test[0], test[1])
	end
end

-- Test solution

precore.make_solution(
	"test",
	{"debug", "release"},
	{"x64", "x32"},
	nil,
	{
		"precore-generic",
		"cacophony-deps",
		"cacophony-import"
	}
)

-- Groups

include("general")
include("unit")

action_clean()
