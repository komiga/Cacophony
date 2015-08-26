
local S, G, R = precore.helpers()

precore.import(G"${DEP_PATH}/duct")

precore.make_config_scoped("cacophony.env", {
	once = true,
}, {
{global = function()
	precore.define_group("CACOPHONY", os.getcwd())
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
			G"${CACOPHONY_ROOT}/",
		}
end}})

precore.apply_global({
	"precore.env-common",
	"cacophony.env",
})
