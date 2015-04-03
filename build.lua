
local S, G, R = precore.helpers()

precore.make_config_scoped("trait_wrangler.env", {
	once = true,
}, {
{global = function()
	precore.define_group("TRAIT_WRANGLER", os.getcwd())
end}})

precore.make_config("trait_wrangler.strict", nil, {
{project = function()
	configuration {}
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

precore.make_config("trait_wrangler.dep", nil, {
{project = function()
	configuration {}
		includedirs {
			G"${TRAIT_WRANGLER_ROOT}/",
		}
end}})

precore.apply_global({
	"precore.env-common",
	"trait_wrangler.env",
})
