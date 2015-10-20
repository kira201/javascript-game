//基本
var sprite3d = new jsb.Sprite3D("Sprite3DTest/boss1.obj");
sprite3d.setTexture("Sprite3DTest/boss.png");

//异步创建
jsb.Sprite3D.createAsync(res, this.asyncLoad_Callback, this, i);
var asyncLoad_Callback = function(sprite3d, data) {
	var node = this.getChildByTag(101);
	var s = cc.winSize;
	var width = s.width / this._path.length;
	sprite3d.setPosition(width * (0.5 + data), s.height / 2);
	node.addChild(sprite3d);
}

//动画
var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
sprite.setRotation3D({
	x: 0,
	y: 180,
	z: 0
});
var animation = new jsb.Animation3D("Sprite3DTest/orc.c3b");
if (animation) {
	var animate = new jsb.Animate3D(animation);
	animate.setSpeed(1);
	sprite.runAction(new cc.RepeatForever(animate));
}
//多个动画
var sprite = new jsb.Sprite3D("Sprite3DTest/tortoise.c3b");
var animation = new jsb.Animation3D("Sprite3DTest/tortoise.c3b");
if (animation) {
	var animate = new jsb.Animate3D(animation, 0, 1.933);
	this._swim = new cc.RepeatForever(animate);
	sprite.runAction(this._swim);

	this._swim.retain();
	this._hurt = new jsb.Animate3D(animation, 1.933, 2.8);
	this._hurt.retain();

	this._state = State.SWIMMING;
}
//action
cc.rotateBy(1, {
	x: 0,
	y: 180,
	z: 0
});

//attach weapon
var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
sprite.setRotation3D(cc.math.vec3(0, 180, 0));
var sp = new jsb.Sprite3D("Sprite3DTest/axe.c3b");
sprite.getAttachNode("Bip001 R Hand").addChild(sp);
sprite.removeAllAttachNode();

//change skin
var sprite = new jsb.Sprite3D("Sprite3DTest/ReskinGirl.c3b");
var curSkin: ["Girl_UpperBody01", "Girl_LowerBody01", "Girl_Shoes01", "Girl_Hair01", "Girl_Face01", "Girl_Hand01", ""];
var SkinType = {
	UPPER_BODY: 0,
	PANTS: 1,
	SHOES: 2,
	HAIR: 3,
	FACE: 4,
	HAND: 5,
	GLASSES: 6,
	MAX_TYPE: 7
};

for (var i = 0; i < sprite.getMeshCount(); i++) {
	var mesh = sprite.getMeshByIndex(i);
	var isVisible = false;
	for (var j = 0; j < SkinType.MAX_TYPE; j++) {
		if (mesh.getName() == curSkin[j]) {
			isVisible = true;
			break;
		}
	}
	mesh.setVisible(isVisible);
}

//包围盒
var aabb = sprite.getAABB();
var obbt = cc.math.obb(aabb);
var mat = sprite.getNodeToWorldTransform3D();
obbt.xAxis.x = mat[0];
obbt.xAxis.y = mat[1];
obbt.xAxis.z = mat[2];
obbt.xAxis.normalize();
obbt.yAxis.x = mat[4];
obbt.yAxis.y = mat[5];
obbt.yAxis.z = mat[6];
obbt.yAxis.normalize();
obbt.zAxis.x = -mat[8];
obbt.zAxis.y = -mat[9];
obbt.zAxis.z = -mat[10];
obbt.zAxis.normalize();
obbt.center = this._sprite.getPosition3D();
var corners = cc.math.obbGetCorners(obbt);
//draw
var drawNode = new cc.DrawNode3D();
drawNode.clear();
drawNode.drawCube(corners, cc.color(0, 0, 255));
//碰撞检测
cc.math.obbIntersectsObb(obbt, anotherObb)
//aabb:轴对齐包围盒 不能旋转
var aabb = cc.math.aabb(cc.math.vec3(-10, -10, -10), cc.math.vec3(10, 10, 10));
//obb:有向包围盒  具有方向性 可以旋转
var obb = cc.math.obb(aabb);
obb.center = cc.math.vec3(x, y, z);
//touch test
var location = touches[0].getLocationInView();
var ray = calculateRayByLocationInView(location);
cc.math.rayIntersectsObb(ray, obb)
function calculateRayByLocationInView(location) {
	var camera = cc.Camera.getDefaultCamera();
	var src = cc.math.vec3(location.x, location.y, -1);
	var nearPoint = camera.unproject(src);

	src = cc.math.vec3(location.x, location.y, 1);
	var farPoint = camera.unproject(src);

	var direction = cc.math.vec3(farPoint.x - nearPoint.x, farPoint.y - nearPoint.y, farPoint.z - nearPoint.z);
	direction.normalize();

	return cc.math.ray(nearPoint, direction);
}

//mirror
var sprite = new jsb.Sprite3D("Sprite3DTest/orc.c3b");
sprite.setScaleX(-1);

//API
sprite.setCullFace(gl.FRONT);//剔除哪个面 gl_BACK gl_FRONT_AND_BACK
sprite.getAttachNode(boneName); //通过传入一个骨骼名获得该骨骼
sprite.removeAttachNode(boneName); //删除传入骨骼名的骨骼
sprite.getMeshCount();
sprite.getMeshByIndex();
sprite.getMeshByName();
sprite.setTexture(fileName);
sprite.setNormalizedPosition(cc.p(0.5, 0.5));
sprite.setRotation3D(cc.math.vec3(90, 0, 0));
sprite.setForceDepthWrite(true);
//rotationquat
var quat = cc.math.quaternion(cc.math.vec3(0, 0, 1), accAngle - Math.PI * 0.5);
sprite.setRotationQuat(quat);