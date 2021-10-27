function result = hu_moment(shape, m)
%Y'all are really making me work for this one, huh
if m == 1
    result = normalized_moment(shape,2, 0) + normalized_moment(shape,0, 2);
elseif m == 2
    result = (normalized_moment(shape,2, 0)+ normalized_moment(shape,0, 2))^2 + (2*normalized_moment(shape,1, 1)^2);
elseif m == 3
    result = (normalized_moment(shape,3, 0) - 3*normalized_moment(shape,1, 2))^2 + (3*normalized_moment(shape,2, 1) - normalized_moment(shape,0, 3))^2;
elseif m == 4
    result = (normalized_moment(shape,3, 0) - normalized_moment(shape,1, 2))^2 + (normalized_moment(shape,2, 1) + normalized_moment(shape,0, 3))^2;
elseif m == 5 
    coef1 = (normalized_moment(shape,3, 0) -3*normalized_moment(shape,1, 2)) * (normalized_moment(shape,3, 0) + normalized_moment(shape,1, 2));
    squares1 = ((normalized_moment(shape,3, 0) + normalized_moment(shape,1, 2))^2 - 3* (normalized_moment(shape,2, 1) + normalized_moment(shape,0, 3))^2);
    coef2 = (3*normalized_moment(shape,2, 1) - normalized_moment(shape,0, 3)) * (normalized_moment(shape,2, 1) + normalized_moment(shape,0, 3));
    squares2 = (3*(normalized_moment(shape,3, 0) + normalized_moment(shape,1, 2))^2 - (normalized_moment(shape,2, 1) + normalized_moment(shape,0,3))^2);
    result = coef1 * squares1 + coef2 * squares2;
elseif m == 6
    coef1 = normalized_moment(shape,2, 0) - normalized_moment(shape,0, 2);
    squares = (normalized_moment(shape,3, 0) + normalized_moment(shape,1, 2)^2) - (normalized_moment(shape,2, 1) + normalized_moment(shape,0, 3)^2);
    weirdChunk = 4 * normalized_moment(shape,1, 1) * (normalized_moment(shape,3, 0)+normalized_moment(shape,1, 2)) * (normalized_moment(shape,2, 1) + normalized_moment(shape,0 , 3));
    result = coef1 * squares + weirdChunk; 
elseif m == 7
    coef1 = (3*normalized_moment(shape,2, 1) - normalized_moment(shape,0, 3)) * (normalized_moment(shape,3, 0) + normalized_moment(shape,1, 2));
    squares1 = ((normalized_moment(shape,3, 0) + normalized_moment(shape,1, 2))^2 - 3* (normalized_moment(shape,2, 1) + normalized_moment(shape,0, 3))^2);
    coef2 = (normalized_moment(shape,3, 0) -3*normalized_moment(shape,1, 2)) * (normalized_moment(shape,2, 1) + normalized_moment(shape,0, 3));
    squares2 = (3*(normalized_moment(shape,3, 0) + normalized_moment(shape,1, 2))^2 - (normalized_moment(shape,2, 1) + normalized_moment(shape,0, 3))^2);
    result = coef1 * squares1 - coef2 * squares2;
end
end

