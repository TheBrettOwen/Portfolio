function result = normalized_moment(shape,i, j)
temp = 0; 
if i == 1 && j == 0
    temp = (central_moment(shape,i, j))/(central_moment(shape,0, 0));
elseif i ==0 && j ==1
    temp = (central_moment(shape,i, j))/(central_moment(shape,0, 0));
else
    temp = (central_moment(shape,i, j))/(central_moment(shape,0, 0)^(1+(i+j)/2));
end

   
result = temp;
end

