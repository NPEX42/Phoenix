X = 0;
Y = 0;
W = 0;
ANGLE = 0;


function Init()
    W = math.random(10, 100);
    ANGLE = math.random() * math.pi * 2;
end

function Render()
    DrawRotatedSprite(X, Y, W, W, ANGLE, "Snom");
end

function Update()
    X = X + math.random(-10, 10);
    Y = Y + math.random(-10, 10);
    if X < 50 then
        X = 50;
    end

    if Y < 50 then
        Y = 50;
    end

    if X > (720 - 50) then
        X = (720 - 50);
    end

    if Y > (480 - 50) then
        Y = (480 - 50);
    end
end