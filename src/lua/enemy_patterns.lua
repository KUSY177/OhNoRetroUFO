-- enemy_patterns.lua
-- Здесь можно описывать сложные паттерны движения

EnemyPatterns = {}

EnemyPatterns["basic"] = function(enemy, dt)
    -- простой враг: медленно опускается вниз
    enemy.y = enemy.y + 50 * dt
end

EnemyPatterns["zigzag"] = function(enemy, dt)
    enemy.y = enemy.y + 60 * dt
    enemy.x = enemy.x + math.sin(enemy.y * 0.1) * 50 * dt
end
