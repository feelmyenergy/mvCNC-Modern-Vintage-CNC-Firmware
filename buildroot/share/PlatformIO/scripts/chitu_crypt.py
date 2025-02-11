#
# chitu_crypt.py
# Customizations for Chitu boards
#
import pioutil
if pioutil.is_pio_build():
	import os,random,struct,uuid,mvcnc
	# Relocate firmware from 0x08000000 to 0x08008800
	mvcnc.relocate_firmware("0x08008800")

	def calculate_crc(contents, seed):
		accumulating_xor_value = seed;

		for i in range(0, len(contents), 4):
			value = struct.unpack('<I', contents[ i : i + 4])[0]
			accumulating_xor_value = accumulating_xor_value ^ value
		return accumulating_xor_value

	def xor_block(r0, r1, block_number, block_size, file_key):
		# This is the loop counter
		loop_counter = 0x0

		# This is the key length
		key_length = 0x18

		# This is an initial seed
		xor_seed = 0x4BAD

		# This is the block counter
		block_number = xor_seed * block_number

		#load the xor key from the file
		r7 =  file_key

		for loop_counter in range(0, block_size):
			# meant to make sure different bits of the key are used.
			xor_seed = int(loop_counter / key_length)

			# IP is a scratch register / R12
			ip = loop_counter - (key_length * xor_seed)

			# xor_seed = (loop_counter * loop_counter) + block_number
			xor_seed = (loop_counter * loop_counter) + block_number

			# shift the xor_seed left by the bits in IP.
			xor_seed = xor_seed >> ip

			# load a byte into IP
			ip = r0[loop_counter]

			# XOR the seed with r7
			xor_seed = xor_seed ^ r7

			# and then with IP
			xor_seed = xor_seed ^ ip

			#Now store the byte back
			r1[loop_counter] = xor_seed & 0xFF

			#increment the loop_counter
			loop_counter = loop_counter + 1

	def encrypt_file(input, output_file, file_length):
		input_file = bytearray(input.read())
		block_size = 0x800
		key_length = 0x18

		uid_value = uuid.uuid4()
		file_key = int(uid_value.hex[0:8], 16)

		xor_crc = 0xEF3D4323;

		# the input file is exepcted to be in chunks of 0x800
		# so round the size
		while len(input_file) % block_size != 0:
			input_file.extend(b'0x0')

		# write the file header
		output_file.write(struct.pack(">I", 0x443D2D3F))
		# encrypt the contents using a known file header key

		# write the file_key
		output_file.write(struct.pack("<I", file_key))

		#TODO - how to enforce that the firmware aligns to block boundaries?
		block_count = int(len(input_file) / block_size)
		print ("Block Count is ", block_count)
		for block_number in range(0, block_count):
			block_offset = (block_number * block_size)
			block_end = block_offset + block_size
			block_array = bytearray(input_file[block_offset: block_end])
			xor_block(block_array, block_array, block_number, block_size, file_key)
			for n in range (0, block_size):
				input_file[block_offset + n] = block_array[n]

			# update the expected CRC value.
			xor_crc = calculate_crc(block_array, xor_crc)

		# write CRC
		output_file.write(struct.pack("<I", xor_crc))

		# finally, append the encrypted results.
		output_file.write(input_file)
		return

	# Encrypt ${PROGNAME}.bin and save it as 'update.cbd'
	def encrypt(source, target, env):
		firmware = open(target[0].path, "rb")
		update = open(target[0].dir.path + '/update.cbd', "wb")
		length = os.path.getsize(target[0].path)

		encrypt_file(firmware, update, length)

		firmware.close()
		update.close()

	mvcnc.add_post_action(encrypt);
