% gauss elimination w/ scaled partial pivoting
function [x, index] = math135_project1_moya_branden()    
    % setup
    promptn = 'Enter n: ';
    promptA = 'Enter A: ';
    promptb = 'Enter b: ';

    n = input(promptn);
    A = input(promptA);
    b = input(promptb);
    
    index = (1:n)';
    scale = zeros(1,n);
    
    for i = 1:n
        scale(i) = max( abs(A(i,:)) );
    end 
    
    %gauss start
    for i = 1:(n-1)
        r = abs( A(index(i),i) / scale(index(i)) );
        ihold = i;

        for j = (i+1):n
            t = abs( A(index(j),i) / scale(index(j)) ); 
            if t > r
                r = t;  
                ihold = j;  
            end
        end

        temp = index(ihold);
        index(ihold) = index(i);
        index(i) = temp; 

        for j = (i+1):n
            A(index(j),i) = A(index(j),i) / A(index(i),i);
            for k = (i+1):n
                A(index(j),k) = A(index(j),k) - A(index(j),i) * A(index(i),k);
            end
        end
    end
    
    % backwards sub
    y = zeros(n,1);       
    y(1) = b(index(1));

    for i = 2:n
        y(i) = b(index(i));
        for j = 1:(i-1)
            y(i) = y(i) - A(index(i),j) * y(j);
        end
    end
    
    x = zeros(n,1);  
    x(n) = y(n)/A(index(n),n);
    
    for i = (n-1):-1:1
        x(i) = y(i);
        for j = (i+1):n
            x(i) = x(i) - A(index(i),j) * x(j);
        end
        x(i) = x(i) / A(index(i),i);
    end
end 