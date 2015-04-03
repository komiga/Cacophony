
local S, G, R = precore.helpers()

precore.make_config_scoped("cacophony.env", {
	once = true,
}, {
{global = function()
	precore.env_global({
		CACOPHONY_ROOT = os.getcwd(),
	}, true)
end}})

precore.make_config("cacophony.strict", nil, {
{project = function()
	configuration {"clang"}
		flags {
			"FatalWarnings"
		}

	configuration {"linux"}
		buildoptions {
			"-pedantic-errors",
			"-Wextra",

			"-Wuninitialized",
			"-Winit-self",

			"-Wmissing-field-initializers",
			"-Wredundant-decls",

			"-Wfloat-equal",
			"-Wold-style-cast",

			"-Wnon-virtual-dtor",
			"-Woverloaded-virtual",

			"-Wunused",
			"-Wundef",
		}
end}})

precore.make_config("cacophony.dep", nil, {
"duct.dep",
{project = function()
	configuration {}
		includedirs {
			S"${CACOPHONY_ROOT}/",
		}
end}})

precore.apply_global({
	"precore.env-common",
	"cacophony.env",
})
precore.import(S"${DEP_PATH}/duct")
