local component = require("component")
local string = require("string")
local term = require("term")
local internet = component.internet
local cardwriter = component.os_cardwriter

local connection = internet.connect("127.0.0.1", 8001)
connection.finishConnect()
term.write("Count: ")
connection.write("CREATE " .. term.read())
local id = 0
local buffer = connection.read(4)
connection.close()
id = string.byte(buffer, 1) * 256 * 256 * 256 + string.byte(buffer, 2) * 256 * 256 + string.byte(buffer, 3) * 256 + string.byte(buffer, 4)
cardwriter.write(tostring(id), "Travel Card")