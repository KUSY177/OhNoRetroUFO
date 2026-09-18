require("enemy_patterns")

local time_acc = 0
local wave = 1

function update_wave(dt)
    time_acc = time_acc + dt

    -- первая волна: три обычных НЛО
    if wave == 1 and time_acc > 1.0 then
        spawn_enemy("basic", 100, 50)
        spawn_enemy("basic", 300, 50)
        spawn_enemy("basic", 500, 50)
        wave = 2
    end

    -- вторая волна: тяжёлые враги
    if wave == 2 and time_acc > 3.0 then
        spawn_enemy("heavy", 200, 30)
        spawn_enemy("heavy", 400, 30)
        wave = 3
    end

    -- третья волна: быстрые зигзаги
    if wave == 3 and time_acc > 5.0 then
        spawn_enemy("fast", 150, 40)
        spawn_enemy("fast", 350, 40)
        spawn_enemy("fast", 550, 40)
        wave = 4
    end
end
