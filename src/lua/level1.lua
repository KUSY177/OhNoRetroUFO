-- level1.lua

local time_acc = 0
local wave = 1

function update_wave(dt)
    time_acc = time_acc + dt

    if wave == 1 and time_acc > 1.0 then
        -- первая простая волна: три НЛО
        spawn_enemy("basic", 100, 50)
        spawn_enemy("basic", 300, 50)
        spawn_enemy("basic", 500, 50)
        wave = 2
    elseif wave == 2 and time_acc > 3.0 then
        -- вторая волна: зигзаг
        spawn_enemy("zigzag", 200, 30)
        spawn_enemy("zigzag", 400, 30)
        wave = 3
    end
end
