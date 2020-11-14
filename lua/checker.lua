local event = require("event")
local component = require("component")
local string = require("string")
local os = require("os")
local computer = component.computer
local redstone = component.redstone
local rfidreader = component.os_rfidreader
local internet = component.internet
local gpu = component.gpu

function clear()
    gpu.setResolution(6, 3)
    gpu.fill(1, 1, 6, 3, " ")
end

clear()

while true do
    local card = rfidreader.scan(1)[1]
    if (card ~= nil) then
        local connection = internet.connect("127.0.0.1", 8001)
        connection.finishConnect()
        connection.write("GO " .. card.data)
        local msg = connection.read(2)
        local count = 0
        if msg == "OK" then
            local buffer = connection.read(4)
            count = string.byte(buffer, 1) * 256 * 256 * 256 + string.byte(buffer, 2) * 256 * 256 + string.byte(buffer, 3) * 256 + string.byte(buffer, 4)
            gpu.set(1, 1, "Now:")
            gpu.set(2, 2, tostring(count))
            redstone.setOutput(1, 15)
            os.sleep(2)
            redstone.setOutput(1, 0)
        elseif msg == "EC" then
            gpu.set(1, 2, "Your=0")
            computer.beep(1200, 0.1)
            os.sleep(0.1)
            computer.beep(1200, 0.1)
            os.sleep(0.1)
            computer.beep(1200, 0.1)
            os.sleep(2)
        end
        clear()
        connection.close()
    end
end