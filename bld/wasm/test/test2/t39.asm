.model small
.data

	dw '1'
	dw '12'
	dd '1'
	dd '12'
	dd '123'
	dd '1234'
	df '1'
	df '12'
	df '123'
	df '1234'
	df '12345'
	df '123456'
	dq '1'
	dq '12'
	dq '123'
	dq '1234'
	dq '12345'
	dq '123456'
	dq '1234567'
	dq '12345678'
	dt '1'
	dt '12'
	dt '123'
	dt '1234'
	dt '12345'
	dt '123456'
	dt '1234567'
	dt '12345678'
	dt '123456789'
	dt '1234567890'
ifdef errors
	dw '123'
	dd '12345'
	df '123467'
	dq '123456789'
	dt '12345678901'
endif

end