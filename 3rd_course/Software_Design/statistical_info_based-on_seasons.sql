WITH SortedRows AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY Month_name) AS RowNumber
    FROM (
        SELECT 
            (CASE MONTH(TARIX)
                WHEN 3  THEN N'Spring'
                WHEN 6  THEN N'Summer'
                WHEN 9  THEN N'Fall'
                WHEN 12 THEN N'Winter'
                ELSE ''
            END) AS Season_name,
            (CASE MONTH(TARIX)
                WHEN 1 THEN '(01) January' WHEN 2 THEN '(02) February' WHEN 3 THEN '(03) March' WHEN 4 THEN '(04) April'
                WHEN 5 THEN '(05) May' WHEN 6 THEN '(06) June' WHEN 7 THEN '(07) July' WHEN 8 THEN '(08) August'
                WHEN 9 THEN '(09) September' WHEN 10 THEN '(10) October' WHEN 11 THEN '(11) November' WHEN 12 THEN '(12) December'
            END) AS Month_name,
            SUM(ODENIS) AS Payment
        FROM BORCH
        GROUP BY MONTH(TARIX)
    ) AS New_T
)

SELECT Season_name, Month_name, concat(Payment, ' azn') as Payment,
(case Month_name 
		when '(05) May' then (select concat('= ', str(sum(Payment), 10, 2), ' azn') from SortedRows 
							  where Month_name = '(03) March' or Month_name = '(04) April' or Month_name = '(05) May')
		
		when '(08) Avqust' then (select concat('= ', str(sum(Payment), 10, 2), ' azn') from SortedRows 
							  where Month_name = '(06) June' or Month_name = '(07) July' or Month_name = '(08) August')
		
		when '(11) November' then (select concat('= ', str(sum(Payment), 10, 2), ' azn') from SortedRows 
						      where Month_name = '(09) September' or Month_name = '(10) OCtober' or Month_name = '(11) November')
		when '(02) Fevral' then (select concat('= ', str(sum(Payment), 10, 2), ' azn') from SortedRows 
							     where Month_name = '(12) December' or Month_name = '(01) January' or Month_name = '(02) February')
		else '+' end) as Total_Payment
FROM SortedRows 
ORDER BY CASE WHEN RowNumber = 1 THEN 999998
			  WHEN RowNumber = 2 THEN 999999
			  ELSE RowNumber END;
