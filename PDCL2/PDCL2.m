N = 700; % Change this value to modify the matrix size

M1 = randi([0, 100], N, N);
M2 = randi([0, 100], N, N);
M3 = zeros(N, N);

% Row-major addition
tic;
for i = 1:N
    for j = 1:N
        M3(i, j) = M1(i, j) + M2(i, j);
    end
end
row_time = toc;
fprintf('Row Major Execution Time: %.6f seconds\n', row_time);

% Column-major addition
tic;
for j = 1:N
    for i = 1:N
        M3(i, j) = M1(i, j) + M2(i, j);
    end
end
col_time = toc;
fprintf('Column Major Execution Time: %.6f seconds\n', col_time);

% Direct addition
tic;
M3 = M1 + M2;
dir_time = toc;
fprintf('Direct Addition Execution Time: %.6f seconds\n', dir_time);
