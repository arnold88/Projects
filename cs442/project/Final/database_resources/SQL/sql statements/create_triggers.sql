CREATE TRIGGER check_transaction_time BEFORE INSERT ON orders
FOR EACH ROW
BEGIN
	IF NEW.transaction_second > 60
		OR NEW.transaction_second < 0
		OR NEW.transaction_minute > 60
		OR NEW.transaction_minute < 0
		OR NEW.transaction_hour > 24
		OR NEW.transaction_hour < 0
		OR NEW.transaction_day > 31
		OR NEW.transaction_day < 0
		OR NEW.transaction_month > 12
		OR NEW.transaction_month < 0
		OR NEW.transaction_year < 2000
	THEN
    		SIGNAL SQLSTATE '12345';
    	END IF;
END;


CREATE TRIGGER check_credit_card BEFORE INSERT ON payment_methods
FOR EACH ROW
BEGIN
	IF LENGTH(NEW.credit_card_number) > 16
		OR LENGTH(NEW.credit_card_number) < 16
		OR NEW.expiration_month > 12
		OR NEW.expiration_month < 0
		OR NEW.expiration_year < 2000
	THEN
    		SIGNAL SQLSTATE '12345';
    	END IF;
END;

CREATE TRIGGER check_reviews BEFORE INSERT ON reviews
FOR EACH ROW
BEGIN
	IF NEW.rating < 0
		OR NEW.rating > 5
	THEN
    		SIGNAL SQLSTATE '12345';
    	END IF;
END;

