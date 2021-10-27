%test script 

% Replace this path with your cs4379c-fall2021 git repository path in your system.
repo_path = 'D:\cs4379c-fall2021-source';

s = filesep; % This gets the file separator character from the  system
addpath([repo_path s 'Data' s '03_elementary_image_operations' s 'images'])
addpath([repo_path s 'Code' s '00_common' s '00_detection'])
addpath([repo_path s 'Code' s '00_common' s '00_images'])
addpath([repo_path s 'Code' s '00_common' s '00_utilities'])
addpath([repo_path s 'HW8'])
addpath([repo_path s 'HW8' s 'training_data'])

image = read_gray('fcircle.bmp');
image = image > 0; 

load_mnist();

load('database.mat')

classifyTest = zeros(1,5000)
true_positives = 0; 
for a = 5001:10000
    index = a-5000;
    digit = mnist_digits(:,:,a); % Digit is 9
    digit_number = mnist_labels(a);
    classifyTest(index) = classify_digit_cm(digit, database);
    if classifyTest(index) == digit_number
        true_positives = true_positives + 1;  
    end
end