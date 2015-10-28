/*
 * AIControl.hpp
 *
 * The AI controlling algorithms, packed into a singleton class
 * @author: wysiwyng
 */

#ifndef AICONTROL_H_
#define AICONTROL_H_
namespace rcurse {
class AIControl {
private:
	AIControl();
	AIControl(const AIControl&);
public:
	static AIControl& instance();

	virtual ~AIControl();

};
}
#endif /* AICONTROL_H_ */
