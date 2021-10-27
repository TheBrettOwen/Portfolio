function result = classify_digit_cm(digit,database)
    digitBW = imbinarize(digit);

    digitMoments = zeros(10, 1);
    for a = 1:10
        digitMoments(a) = central_moment(digitBW, a-1, 11-a);
    end
    
    distances = zeros(1, 5000);
    
    for a = 1:5000
        tempVector1 = zeros(10,a); %#ok<PREALL>
        tempVector1 = database(1:10, a);
        tempVector1 = tempVector1(:);
        tempVector2 = digitMoments(:);
        
        distances(a) = sqrt(sum(sum((tempVector2-tempVector1).^2)));
    end
    nearest = min(distances);
    nearestIndex = find(distances == nearest);
    result = database (11, nearestIndex);
  
end

