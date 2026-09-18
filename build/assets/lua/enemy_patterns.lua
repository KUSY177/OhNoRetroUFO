EnemyPatterns = {}

EnemyPatterns["basic"] = function(e, dt)
    e.y = e.y + 80 * dt
end

EnemyPatterns["fast"] = function(e, dt)
    e.y = e.y + 140 * dt
    e.x = e.x + math.sin(e.y * 0.1) * 60 * dt
end

EnemyPatterns["heavy"] = function(e, dt)
    e.y = e.y + 50 * dt
end

function enemy_update(e, dt)
    local pattern = EnemyPatterns[e.type]
    if pattern then
        pattern(e, dt)
    else
        e.y = e.y + 40 * dt
    end
    return e
end
