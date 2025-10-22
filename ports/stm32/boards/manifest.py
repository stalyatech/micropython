include("$(MPY_DIR)/extmod/asyncio")
freeze('$(MPY_DIR)/extmod', script='typing.mpy')
module('utoml.py', base_path='$(MPY_DIR)/extmod/utoml', opt=2)

require("dht")
require("onewire")
require('functools')
require('logging')
