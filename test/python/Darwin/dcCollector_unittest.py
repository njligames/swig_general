
import evr 


def main():
	dc = evr.DCCollector('VLayout')
	dc.add_layout('HLayout')
	dc.add_component('Text', '{"Title":"s Hdr0","Body":"Rusty Texture"}')
	dc.add_component('Image', '{"Title":"texture","Uuid":"730ad959-4bf9-4252-be59-612ad944050f","Updating": true}');
	dc.add_component('Button', '{"Title":"The Button","Action":"Perform task"}')
	dc.add_layout('HLayout')
	dc.add_component('Text', '{"Title":"s Hdr1","Body":"UFO Screenshot"}')
	dc.add_component('Image', '{"Title":"thumbnail","Uuid":"874cea83-d897-4280-b066-b7eeba010fc1","Updating": false}');
	dc.add_component('Checkbox', '{"Title":"Validate Test","value":true}')

	print dc.to_string()
	print 'Test done'


if __name__ == '__main__':
	main()
