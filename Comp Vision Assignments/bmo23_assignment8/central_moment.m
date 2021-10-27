function result = central_moment(shape,i, j)
[r, c] = size(shape); 

xHat = (rawMoment(shape, 1, 0))/(rawMoment(shape, 0, 0)); 
yHat = (rawMoment(shape, 0, 1))/(rawMoment(shape, 0, 0)); 

temp = 0;  

for x= 1:r
    for y=1:c
        temp = temp + ((x-xHat)^i) * ((y-yHat)^j )* (shape(x,y));
    end
end
result = temp;
end

