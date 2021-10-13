function result = road_orientation(image) 

A = zeros(180);
Max = 0; 
MaxIndex = 0;

for i = 0:1:180
    angle_im = oriented_edges(image, 1.4, 4, i, 15);
    A(i+1) = sum(angle_im(:));
    if A(i+1) > Max
        Max = A(i+1)
        MaxIndex = i; 
    end
end


result = MaxIndex;
end