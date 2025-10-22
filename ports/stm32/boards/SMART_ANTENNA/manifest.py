include("$(PORT_DIR)/boards/manifest.py")

require("bundle-networking")
module("_boot.py")

package(
	"sdk",
	base_path="$(MPY_DIR)/extmod/sdk/src",
	opt=2,
)
