local evr = require("evr")
print("LUA MODULES:\n",(package.path:gsub("%;","\n\t")),"\n\nC MODULES:\n",(package.cpath:gsub("%;","\n\t")))
local m = evr.Math()
print(m:add(100, 200.1))
-- print(m)


