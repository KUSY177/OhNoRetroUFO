EnemyPatterns = {}

-- универсальная точка входа
function enemy_update(e, dt)
    local pattern = EnemyPatterns[e.type]
    if pattern then
        pattern(e, dt)
    else
        -- fallback если тип неизвестен
        e.y = e.y + 40 * dt
    end
end

-- обычный враг: медленный
EnemyPatterns["basic"] = function(enemy, dt)
    enemy.y = enemy.y + 50 * dt
end

-- быстрый враг: быстрее падает
EnemyPatterns["fast"] = function(enemy, dt)
    enemy.y = enemy.y + 120 * dt
end

-- тяжёлый враг: медленный, но двигается зигзагом
EnemyPatterns["heavy"] = function(enemy, dt)
    enemy.y = enemy.y + 40 * dt
    enemy.x = enemy.x + math.sin(enemy.y * 0.05) * 30 * dt
end
